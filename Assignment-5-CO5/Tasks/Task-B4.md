# Task B4 – Final Engineering Decision: Conversational Interface and Deployment (5 Marks)

Operators want to ask the Task B3 system questions through a chatbot or voice assistant, for example “Which alerts are open?” and “Why was this flagged?”

## B4.1 – Implement a Practical Strategy (2 marks)
Build a retrieval-based chatbot with at least eight intents (TF-IDF with cosine similarity or a classifier) and an out-of-scope fallback controlled by a confidence threshold. Report per-intent precision, recall and F1, confusion matrix and response latency.

## B4.2 – Challenge Your Strategy (1 mark)
Simulate speech-recognition errors by corrupting test utterances at word-error rates of 0%, 10%, 20% and 30%. Report intent accuracy, out-of-scope detection and false-accept rate, and show a threshold-sweep curve.

## B4.3 – Production Decision (2 marks)
Decide whether the detection model and assistant should run on the edge device or in the cloud. Defend the decision using your own latency, accuracy, throughput, privacy and cost evidence, and state conditions under which you would reverse it.

**Evidence expected:** Chatbot code, intent-level metrics, word-error-rate degradation table, threshold curve and evidence-based deployment decision.
