//
// Copyright (c) 2016, Leander Tentrup, Saarland University
//
// Licenced under ISC Licsnse, see ./LICENSE.txt form information
//

#include <assert.h>
#include <stdio.h>

#include "combine.h"
#include "aiger.h"

void print_usage(const char* name) {
    printf("%s <ltl_monitor.aag> <implementation.aag>\n"
           "ltl_monitor.aag has to be generated from smvtoaig tool\n", name);
}

int main(int argc, const char* argv[]) {
    
    if (argc < 2) {
        fprintf(stderr, "Expect at least one input\n");
        print_usage(argv[0]);
        return 1;
    }
    
    const char* monitor_file_name;
    const char* implementation_file_name;
    if (argc == 3) {
        monitor_file_name = argv[1];
        implementation_file_name = argv[2];
    } else {
        assert(argc == 2);
        // monitor is given via stdin
        monitor_file_name = NULL;
        implementation_file_name = argv[1];
    }
    
    aiger* monitor = aiger_init();
    if (monitor == NULL) {
        return 1;
    }
    
    if (monitor_file_name != NULL) {
        if (aiger_open_and_read_from_file(monitor, monitor_file_name) != NULL) {
            fprintf(stderr, "error: cannot read monitor file\n");
            return 1;
        }
    } else {
        if (aiger_read_from_file(monitor, stdin) != NULL) {
            fprintf(stderr, "error: cannot read monitor file\n");
            return 1;
        }
    }
    
    aiger* implementation = aiger_init();
    if (implementation == NULL) {
        return 1;
    }
    
    if (aiger_open_and_read_from_file(implementation, implementation_file_name) != NULL) {
        fprintf(stderr, "error: cannot read implementation file\n");
        return 1;
    }
    
    aiger* combination = combine(monitor, implementation);
    if (combination == NULL) {
        return 1;
    }
    
    assert(!aiger_check(combination));

    //aiger_reencode(combination);
    aiger_write_to_file(combination, aiger_ascii_mode, stdout);
    
    return 0;
}
