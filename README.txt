NOTE: I will first be supporting GNOME Orca (the scriptable screen reader): https://wiki.gnome.org/Projects/Orca

There are five main parts to this system:

1. Raw Data Collection

Use screen reader, screen capture, and microphone/speaker input to collect raw
data from the user.

2. Knowledge Base Lookup

Take the raw data and perform a fast, lossy lookup through a knowledge base.
Based on the raw data, try and find similar content in the knowledge graph that
may be similar in nature to the raw data (e.g., similar questions, text, etc).

3. Informed Inference

Using the raw data as well as data collected from the knowledge base, use some
kind of inferential model to generate the final response, for example, a
solution to the user's question or some similar results that they might find
useful.

4. Display Generated Response

The results need to be displayed to the user in a clear and concise represen-
tation. The results must be easy to skim and relevant to the user's original
query.

They must also show the similarity scores retrieved from the knowledge
base lookup, so that the user can gauge how much of the response comes directly
from the knowledge base vs. the inferential model.

5. Continue in the Event Loop

Respond dynamically to the user's reactions. For example, if the user moves on
to a different page, question, or context, the system should be able to react
to that. This could be via some kind of intelligent signal about the user's st-
ate (e.g., from watching the screen capture or listening to the microphone). It
could also just be triggered by some kind of button press or hotkey.
