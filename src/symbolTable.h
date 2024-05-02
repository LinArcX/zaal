#ifndef KAVEH_SYMBOL_TABLE_H
#define KAVEH_SYMBOL_TABLE_H

#define NSYMBOLS        1024            // Number of symbol table entries
static int Globs = 0;		// Position of next free global symbol slot
static int NextFreeGlobalSlot = 0;                     // Position of next free global symbol slot
extern struct symbolTable GlobalSymbolTable[NSYMBOLS]; // Global symbol table

// Determine if the symbol s is in the global symbol table.
// Return its slot position or -1 if not found.
int findglob(char *s);

// Get the position of a new global symbol slot, or die
// if we've run out of positions.
static int newglob(void);

// Add a global symbol to the symbol table.
// Return the slot number in the symbol table
int addglob(char *name);

#endif
