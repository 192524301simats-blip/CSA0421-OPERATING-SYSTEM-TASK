# Task B2 – Engineer an Adversarial Input for the Expert System (5 Marks)

Implement the Task A3 shell with a pump-fault rule base containing at least 15 rules and five fault types, with HOW and WHY explanations.

## B2.1 – Implement and Evaluate (2 marks)
Use 15 of 30 expert-labelled cases for rule development and keep 15 as a hold-out set. Report diagnosis accuracy, per-fault precision and recall, rules fired per case and sample explanations.

## B2.2 – Engineer Adversarial Cases (2 marks)
Design inputs exposing conflicting rules, missing evidence and dependence on rule order. Predict each outcome before running. Compare at least two conflict-resolution strategies: specificity, priority or recency.

## B2.3 – Knowledge Acquisition Test (1 mark)
Add or edit a rule at run time without changing engine code. Show with a regression run which earlier diagnoses were affected.

**Evidence expected:** Shell code, hold-out results, adversarial case table with predictions/outcomes, strategy comparison and regression result.
