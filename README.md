# CoreWarS19

CoreWar (School 42 version) implementation

CoreWar is an old development game, the goal is to make a champion and make it fight in an arena with other champions.

# Objectives

- Make an asm code compiler 
- Make a basic vm capable of executing the champions code
- Create a basic champion (doesn't have to beat anything, the school organises championships every year)

# How did we do it?

Since the pdf they give is intentionally hard to understand our first step was to understand how asm code works and what every available operation does.

At the same time we started to construct a basic structure for our project as to not lose any time.
Once we had a good comprehension of how everything worked we started working hard on it.

### Asm
There really wasn't a lot of information given for this part so most of it was reverse engineering (as in testing a lot of use cases)
I feel really proud of this one as it is very close from the given asm executable (just 1 error is handled differently)

### VM
Seb and Charles did a great job reproducing the given vm executable, they also had to figure out some quirks of how some stuff works (the carry value for example)

### Online
This was basically an introduction to networking in C for nathan, it's a very simple yet complicated thing to do.

# Group repartition

- Asm: Wbraeckm (@Williambraecky)
- VM: Sdespie (@sdespie) and Cvan-bee (@CharlesAntoineVB)
- Online (bonus part, basic networking client and server): Nrouvroy (@rouvroyn)

# Usage

First of all use the make command to compile everything (only tested on macos)

### Asm
 ./asm file
 - No option
 
 Compiles a .s file into a .cor file to be used for the vm

### VM
 ./corewar for instructions
 
 Run a battle between one or more champions
 
### Client
 ./online server_ip champion(.s|.cor)
 
 Connects the client to the specified server

### Server
 ./server
 
 Starts a corewar server
