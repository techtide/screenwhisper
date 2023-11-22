#include <iostream>
#include <ncurses.h>

struct AggregatorState
{
  bool screenChecked;
  bool microphoneChecked;
  bool websiteChecked;
};

// Function to draw the Aggregator panel
void drawAggregatorPanel(WINDOW *aggregatorWin, const AggregatorState &state)
{
  box(aggregatorWin, 0, 0);
  mvwprintw(aggregatorWin, 1, 2, "Aggregator");
  mvwprintw(aggregatorWin, 3, 2, "[ ] Screen");
  mvwprintw(aggregatorWin, 4, 2, "[ ] Microphone");
  mvwprintw(aggregatorWin, 5, 2, "[ ] Website");

  // Toggle check marks based on state
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
  box(knowledgeBaseWin, 0, 0);
  mvwprintw(knowledgeBaseWin, 1, 2, "Knowledge Base");
  // Add text or information here
  wrefresh(knowledgeBaseWin);
}

// Function to draw the Inference panel
void drawInferencePanel(WINDOW *inferenceWin)
{
  box(inferenceWin, 0, 0);
  mvwprintw(inferenceWin, 1, 2, "Inference");
  // Add content specific to Inference here
  wrefresh(inferenceWin);
}

int main()
{
  initscr(); // initialize the library
  noecho();  // don't display input characters
  cbreak();  // disable line buffering

  int height, width;
  getmaxyx(stdscr, height, width);

  // Create windows for each panel
  WINDOW *aggregatorWin = newwin(7, width / 3, 1, 0);
  WINDOW *knowledgeBaseWin = newwin(height - 8, width / 3, 8, 0);
  WINDOW *inferenceWin = newwin(height - 1, 2*width / 3, 1, width / 3);

  // Refresh windows
  refresh();
  wrefresh(aggregatorWin);
  wrefresh(knowledgeBaseWin);
  wrefresh(inferenceWin);

  // Initialize state
  AggregatorState state = {false, false, false};

  // Draw initial content for each panel
  drawAggregatorPanel(aggregatorWin, state);
  drawKnowledgeBasePanel(knowledgeBaseWin);
  drawInferencePanel(inferenceWin);

  int ch;
  while ((ch = getch()) != KEY_F(1))
  {
    // Update state based on user input
    switch (ch)
    {
    case 's':
      state.screenChecked = !state.screenChecked;
      break;
    case 'm':
      state.microphoneChecked = !state.microphoneChecked;
      break;
    case 'w':
      state.websiteChecked = !state.websiteChecked;
      break;
    }

    // Redraw UI based on updated state
    drawAggregatorPanel(aggregatorWin, state);
  }

  // Clean up and exit
  endwin();

  return 0;
}
