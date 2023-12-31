#include <iostream>
#include <ncurses.h>
#include <libconfig.h++>
#include <vector>

#include "aggregator/aggregator.h"
#include "inference/inference.h"
#include "knowledge/knowledge.h"

struct ApplicationState
{
  bool collectingData;
  bool screenChecked;
  bool microphoneChecked;
  bool websiteChecked;
  int data_collected;
};

libconfig::Config screenwhisper_user_config_;

// Function to draw the Aggregator panel
void drawAggregatorPanel(WINDOW *aggregatorWin, const ApplicationState &state)
{
  werase(aggregatorWin);

  box(aggregatorWin, 0, 0);
  std::string kb_collected = std::to_string(state.data_collected) + " KB collected";
  mvwprintw(aggregatorWin, 1, 2, "Aggregator: Disabled (d to toggle)");
  mvwprintw(aggregatorWin, 2, 2, "%s", kb_collected.c_str());
  mvwprintw(aggregatorWin, 3, 2, "[ ] Screen");
  mvwprintw(aggregatorWin, 4, 2, "[ ] Microphone");
  mvwprintw(aggregatorWin, 5, 2, "[ ] Website");

  // Toggle check marks based on state
  if (state.collectingData)
    mvwprintw(aggregatorWin, 1, 2, "Aggregator: Enabled (d to toggle) ");
  if (state.screenChecked)
    mvwprintw(aggregatorWin, 3, 2, "[X] Screen");
  if (state.microphoneChecked)
    mvwprintw(aggregatorWin, 4, 2, "[X] Microphone");
  if (state.websiteChecked)
    mvwprintw(aggregatorWin, 5, 2, "[X] Website");

  wrefresh(aggregatorWin);
}

// Function to draw the Knowledge Base panel
void drawKnowledgeBasePanel(WINDOW *knowledgeBaseWin)
{
  werase(knowledgeBaseWin);
  box(knowledgeBaseWin, 0, 0);
  mvwprintw(knowledgeBaseWin, 1, 2, "Knowledge Base");
  // Add text or information here
  wrefresh(knowledgeBaseWin);
}

// Function to draw the Inference panel
void drawInferencePanel(WINDOW *inferenceWin)
{
  werase(inferenceWin);
  box(inferenceWin, 0, 0);
  mvwprintw(inferenceWin, 1, 2, "Inference");
  // Add content specific to Inference here
  wrefresh(inferenceWin);
}

void enableDataCollection()
{
  return;
}

void InitUpdateState() {
  try {
    // TODO(armanbhalla): Note that the file needs to be 1 folder below
    // the current directory, to keep things simple.
    screenwhisper_user_config_.readFile("../screenwhisper.cfg");
  } catch (const libconfig::FileIOException &fioex) {
    std::cerr << "I/O error while reading the configuration file" << std::endl;
    exit(EXIT_FAILURE);
  } catch (const libconfig::ParseException &pex) {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
    exit(EXIT_FAILURE);
  }
}

// Ingests the state and orchestrates aggregator, inference, and knowledge
// submodules accordingly.
void orchestrate(std::vector<ScreenDataObserver> &observers, ApplicationState &state)
{
  // Collect data from each observer
  for (auto &observer : observers)
  {
    if (state.collectingData) {
      observer.CollectData();
    }
  }
}

int main()
{
  ScreenDataObserver screen_observer;
  std::vector<ScreenDataObserver> observerVec;
  observerVec.push_back(screen_observer);

  initscr(); // initialize the library
  noecho();  // don't display input characters
  cbreak();  // disable line buffering

  curs_set(0); // hide the cursor

  InitUpdateState();

  int height, width;
  getmaxyx(stdscr, height, width);

  // Create windows for each panel
  WINDOW *aggregatorWin = newwin(7, width / 3, 1, 0);
  WINDOW *knowledgeBaseWin = newwin(height - 8, width / 3, 8, 0);
  WINDOW *inferenceWin = newwin(height - 1, 2 * width / 3, 1, width / 3);

  // Refresh windows
  refresh();
  wrefresh(aggregatorWin);
  wrefresh(knowledgeBaseWin);
  wrefresh(inferenceWin);

  ApplicationState state = {0, false, false, false, false};

  // Draw initial content for each panel
  drawAggregatorPanel(aggregatorWin, state);
  drawKnowledgeBasePanel(knowledgeBaseWin);
  drawInferencePanel(inferenceWin);

  int ch;
  while ((ch = getch()) != KEY_F(1))
  {
    switch (ch)
    {
    case 'd':
      if (state.collectingData)
      {
        state.collectingData = false;
        state.screenChecked = false;
        state.microphoneChecked = false;
        state.websiteChecked = false;
      }
      else
      {
        state.collectingData = true;
        enableDataCollection();
      }
      break;
    default:
      break;
    }
    orchestrate(observerVec, state);
    drawAggregatorPanel(aggregatorWin, state);
  }

  // Clean up and exit
  endwin();

  return 0;
}
