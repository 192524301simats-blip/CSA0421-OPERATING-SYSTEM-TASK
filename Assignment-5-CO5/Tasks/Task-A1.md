# Task A1 – Design an Agent Architecture (7 Marks)

**Problem context:** An autonomous parcel-delivery drone must deliver medical parcels across a city grid, avoid no-fly zones and sudden obstacles, cope with wind drift, and return or land safely when battery is low.

## A1.1 – Model the Agent Problem (1 mark)
Specify the PEAS description, classify the environment, and state which agent type(s)—simple reflex, model-based, goal-based, utility-based and learning—the problem requires and why.

## A1.2 – Define Percepts, Internal State and Actions (1 mark)
Define exactly what the drone senses, what it must remember between steps and which actions it may take.

## A1.3 – Define the Decision Rule and Priorities (1 mark)
State how conflicting goals are resolved, for example safety over mission over battery economy, and what utility, if any, trades them off.

## A1.4 – Design Complete Pseudocode (3 marks)
Write pseudocode for the sense–decide–act cycle of a layered or hybrid architecture. Show the reactive safety layer, deliberative planning layer, arbitration, state update and termination. “Plan the route appropriately” is not sufficient.

## A1.5 – Trace the Agent (1 mark)
Manually trace at least six time steps in which an obstacle suddenly appears and the battery falls below a threshold. Show percept, internal state, layer that acted and action chosen at each step.

**Evidence expected:** PEAS and agent-type justification, percept/state/action definitions, priority rule, complete pseudocode and decision trace.
