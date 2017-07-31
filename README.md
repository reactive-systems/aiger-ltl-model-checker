# Model Check AIGER solutions of TLSF synthesis tools

Dependencies:

* `smvtoaig` from AIGER toolset
* `ltl2smv` from NuSMV

Build: `$ make`

Usage:

* Convert TLSF to AIGER monitor: `$ syfco --format smv example.tlsf | smvtoaig > monitor.aag`
* Combine monitor with implementation: `$ ./combine-aiger monitor.aag implementation.aag > combined.aag`
* `combined.aag` can be checked by an arbitrary AIGER model checker