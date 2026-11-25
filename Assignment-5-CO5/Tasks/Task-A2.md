# Task A2 – Don’t Centralise What Can Be Local (5 Marks)

**Problem context:** Flood search-and-rescue with 50 drones. A control station currently assigns every drone its search cell. Communication is unreliable and drones fail during missions.

## A2.1 – Diagnose the Weakness of the Centralised Design (1 mark)
Identify what happens to coverage, communication load and mission success when the controller or links fail.

## A2.2 – Redesign Using Local Rules (2 marks)
Design a decentralised swarm strategy, such as pheromone-like marking, frontier selection or separation/alignment/cohesion rules. Give per-agent pseudocode and state what information an agent needs from neighbours.

## A2.3 – Demonstrate the Emergent Behaviour (1 mark)
On a 5×5 grid with three drones, manually trace several moves to show how the local rule produces coverage without central assignment.

## A2.4 – Challenge Your Rule (1 mark)
Construct a configuration in which the rule causes clustering, deadlock or redundant coverage. Predict the behaviour first, then trace it.

**Evidence expected:** Diagnosis, per-agent rule, hand trace and student-designed failure configuration.
