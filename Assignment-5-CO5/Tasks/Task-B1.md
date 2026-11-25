# Task B1 – Implement and Instrument the Drone Agent (7 Marks)

Implement Task A1 architecture and Task A2 swarm rule in a grid simulator.

## B1.1 – Validate the Implementation (2 marks)
Test at least three scenarios: normal flight, sudden obstacle, and boundary case (battery exhausted or goal blocked). State what each verifies and show behaviour logs.

## B1.2 – Compare Design with Implementation (1 mark)
Compare the Task A1.5 hand trace with the program trace and explain every difference.

## B1.3 – Improve the Design (2 marks)
Introduce swarm coordination for N drones using the Task A2 rule or an improved reactive/deliberative arbitration. State what the improvement targets.

## B1.4 – Measure the Effect (2 marks)
Over at least 30 seeds, compare single-drone and swarm operation on mission success rate, coverage percentage against time, redundancy ratio, battery used, decision latency and robustness when 0%, 10% and 30% of drones fail. Test N=5, 10, 25 and 50.

**Evidence expected:** Simulator and agent code, scenario logs, trace comparison, before/after metric tables and graphs, and scaling interpretation.
