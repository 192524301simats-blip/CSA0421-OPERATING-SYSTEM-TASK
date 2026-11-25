# Task B3 – Applied Case: Full Model versus Edge Model (8 Marks)

Choose one applied case and one public dataset or simulator, and cite the source: (a) AI-based intrusion detection, (b) real-time emotion detection, (c) deepfake detection and face-authenticity verification, (d) disaster detection, (e) AI-powered smart controller, or (f) another instructor-approved edge-AI system. Use the case chosen in Task A5.

## B3.1 – Correctness on a Small Benchmark (2 marks)
Build the full model with a leakage-safe split: time-ordered for intrusion data; subject-wise or source-wise for emotion/deepfake data. Report accuracy, precision, recall, F1, ROC-AUC or PR-AUC and confusion matrix. For the smart-controller case, report settling time, overshoot, energy use and constraint violations against a rule-based baseline.

## B3.2 – Find a Counterexample (2 marks)
Find and categorise at least five mis-predictions. Identify a class of inputs on which the model fails and demonstrate it.

## B3.3 – Increase the Problem Size (2 marks)
Using the Task A4 RDD pipeline in PySpark, process 10^5, 10^6 and 10^7 records (feature extraction or batch scoring). Record runtime for partitions {1,2,4,8}, caching effect and number of shuffles. Explain when more partitions did not improve speed.

## B3.4 – Engineering Trade-Off (2 marks)
Implement the Task A5 compressed model. Report mean and 95th-percentile latency per sample, throughput, model size and accuracy change against the full model. State whether the 50 ms budget is met.

**Evidence expected:** Code, split description, metric tables, error categories, scaling table, compression comparison and interpretation.
