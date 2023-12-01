# FSMLanguage

FSMLanguage is a FSM definition langauge for NFA/DFA research. 
This project provided a parser for loading the FSM and provide a memory model for easily access the FSM.

# Example FSM Definition

```
Robot(found_human, found_enemy) : void {    
    state : stop, move
    state2: fire, ceasefire
    move[found_human==0] -> stop
    stop[found_human==1] -> move
    fire[found_enemy==0] -> ceasefire
    ceasefire[found_enemy==1] -> fire
}
```

We provided a list of API parsing and loading this FSM definition:
```cpp
    fsm::Module mod;
    mod.src = fopen(argv[1], "r");
    mod.Parse();
    fclose(mod.src);
    for (auto p : *(mod.root)) {
        p->print();
    }
```
