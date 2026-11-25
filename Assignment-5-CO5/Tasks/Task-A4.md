# Task A4 – Design a Distributed Data Pipeline with RDDs (4 Marks)

A city air-quality agent receives about 10 million sensor readings `(sensorId, timestamp, value)` per day and needs per-sensor mean and maximum, plus the ten noisiest sensors.

Design the pipeline in pseudocode using RDD operations. Identify:
- Transformations versus actions, and when evaluation happens.
- Narrow transformations versus operations requiring a shuffle.
- Where caching helps and where it wastes memory.
- How lineage allows recovery when a partition is lost.

“Process the data in parallel” is not sufficient.

**Evidence expected:** Complete pipeline pseudocode, narrow/wide classification, caching decision and lineage explanation.
