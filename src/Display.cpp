//
// Created by nelspc on 09/04/25.
//

#include "Display.h"
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/table.hpp>
#include <csignal>
#include <thread>
#include <string>
#include "ElevatorDataTypes.h"

Display::Display(int num_elevators) : receiveSocket(RECEIVE_PORT), numElevators(num_elevators) {
    elevators.resize(numElevators);
    for (int i = 0; i < numElevators; i++) {
        elevators[i].elevatorID = i+1;
        elevators[i].transmittedFloor = 1;
        elevators[i].direction = IDLE;
        elevators[i].capacity = 0;
    }
}


static ftxui::ScreenInteractive* screen_ptr = nullptr;
static std::mutex elevators_mtx;
static std::mutex screen_mtx;

void signal_handler(int signal) {
    if (signal == SIGINT && screen_ptr != nullptr) {
        screen_ptr->Exit();
    }
}

DatagramSocket &Display::getSendSocket() {
    return sendSocket;
}

DatagramSocket &Display::getReceiveSocket() {
    return receiveSocket;
}

void Display::updateThread () {
  while (true) {
      receiveData = wait_and_receive_with_ack("Server", getReceiveSocket(), getSendSocket());
      int index = receiveData.elevatorID;
      if (true) {
          std::lock_guard<std::mutex> lock(elevators_mtx);
          elevators[index - 1].direction = receiveData.direction;
          elevators[index - 1].transmittedFloor = receiveData.transmittedFloor;
          elevators[index - 1].capacity = receiveData.capacity;
      }

      {
          std::lock_guard<std::mutex> lock(screen_mtx);
          if (screen_ptr != nullptr) {
              screen_ptr->PostEvent(ftxui::Event::Custom);
          }
      }
  }
}

void Display::guiThread() {

    std::signal(SIGINT, signal_handler);

    auto render = [&] {
        // Create table data
        std::vector<std::vector<ftxui::Element>> tableData;

        // Add header row
        tableData.push_back({
            ftxui::text("ID") | ftxui::bold | ftxui::hcenter,
            ftxui::text("State") | ftxui::bold | ftxui::hcenter,
            ftxui::text("Floor") | ftxui::bold | ftxui::hcenter,
            ftxui::text("Capacity") | ftxui::bold | ftxui::hcenter,
        });

        std::vector<e_struct> copyElevators;
        if (true) {
            std::lock_guard<std::mutex> lock(elevators_mtx);
            copyElevators = elevators;
        }

        // Add elevator data rows
        for (const auto& e : copyElevators) {
            tableData.push_back({
                ftxui::text(std::to_string(e.elevatorID)),
                ftxui::text(stringDirection(e.direction)) | ftxui::color(
                    e.direction == UP ? ftxui::Color::Green :
                    e.direction == DOWN ? ftxui::Color::Blue :
                    e.direction == IDLE ? ftxui::Color::Yellow :
                    ftxui::Color::Red
                ),
                ftxui::text(std::to_string(e.transmittedFloor)),
                ftxui::text(std::to_string(e.capacity) + "/" + std::to_string(3)),
            });
        }

        // Create table
        ftxui::Table table(std::move(tableData));

        // Style the table
        table.SelectAll().Border(ftxui::LIGHT);
        table.SelectRow(0).Border(ftxui::DOUBLE);
        table.SelectRow(0).Separator(ftxui::LIGHT);

        // Render the table
        return ftxui::vbox({
            ftxui::text("Elevator Monitoring System") | ftxui::bold | ftxui::hcenter,
            ftxui::text("Press Ctrl+C or 'q' to exit") | ftxui::dim | ftxui::hcenter,
            ftxui::separator(),
            ftxui::separatorEmpty(),
            ftxui::separatorEmpty(),
            ftxui::separatorEmpty(),
            table.Render() | ftxui::hcenter,
        });
    };

    auto screen = ftxui::ScreenInteractive::Fullscreen();

    if (true) {
        std::lock_guard<std::mutex> lock(screen_mtx);
        screen_ptr = &screen;
    }


    auto component = ftxui::Renderer(render);
    auto exit_on_q = ftxui::CatchEvent(component, [&](const ftxui::Event& event) {
        if (event == ftxui::Event::Character('q') || event == ftxui::Event::Character('Q')) {
            screen.Exit();
            return true;
        }
        return false;
    });

    screen.Loop(exit_on_q);
}

void Display::run() {
    std::thread update(&Display::updateThread, this);
    guiThread();

    pthread_cancel(update.native_handle());
    update.join();
}

int main(int argc, char *argv[]) {
    int num_elevators = atoi(argv[1]);
    if (num_elevators <= 0) {
        std::cerr << "Number of elevators must be positive." << std::endl;
        return 1;
    }

    Display display(atoi(argv[1]));
    display.run();
}