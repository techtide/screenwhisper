#include <iostream>
#include <ncurses.h>

void drawAggregatorPanel(WINDOW *aggregatorWin) {
    box(aggregatorWin, 0, 0);
    mvwprintw(aggregatorWin, 1, 2, "Aggregator");
    mvwprintw(aggregatorWin, 3, 2, "[ ] Screen");
    mvwprintw(aggregatorWin, 4, 2, "[ ] Microphone");
    mvwprintw(aggregatorWin, 5, 2, "[ ] Website");
    wrefresh(aggregatorWin);
}

void drawKnowledgeBasePanel(WINDOW *knowledgeBaseWin) {
    box(knowledgeBaseWin, 0, 0);
    mvwprintw(knowledgeBaseWin, 1, 2, "Knowledge Base");
    // Add text or information here
    wrefresh(knowledgeBaseWin);
}

void drawInferencePanel(WINDOW *inferenceWin) {
    box(inferenceWin, 0, 0);
    mvwprintw(inferenceWin, 1, 2, "Inference");
    // Add content specific to Inference here
    wrefresh(inferenceWin);
}

int main() {
    initscr();
    noecho();
    cbreak();

    curs_set(0);

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

    // Draw initial content for each panel
    drawAggregatorPanel(aggregatorWin);
    drawKnowledgeBasePanel(knowledgeBaseWin);
    drawInferencePanel(inferenceWin);

    // Wait for user input
    int ch;
    while ((ch = getch()) != KEY_F(1)) {
        // Continue processing based on user input
    }

    // Clean up and exit
    endwin();

    return 0;
}
