
# Hostel Management System (C Language)

A lightweight, console-based **Hostel Management System** developed in **C Programming Language** that allows hostel administrators to securely manage student check-ins, room updates, data removals, and occupancy tracking with persistent binary data storage.

##  Key Features
**Secure Admin Authentication:** Protected by an administrative login gateway requiring a predefined system password (`dev123`) to grant system access.
 **Persistent Binary Database:** Uses optimized binary files (`students.dat`) to store dynamic structures, guaranteeing records are retained permanently across restarts.
 **CRUD Data Management:** Complete utility actions supporting adding new entries, updating existing rows using file pointer offsets, and removing records securely via data staging.
 **Real-Time Room Auditing:** Tracks total operational capacities against current logs to instantly compute remaining unoccupied bed allocations.
 **Occupancy Performance Reports:** Formats flat binary buffers into clean text grids presenting structural data summaries.

## Concepts & Implementation Details
 **Binary File Handling (`stdio.h`):** Employs safe stream wrappers (`fopen`, `fwrite`, `fread`, `fclose`) with custom block configurations (`"ab"`, `"rb+"`) for safe transactional record operations.
 **Pointer Offset Positioning (`fseek`):** Adjusts current system write headers backwards dynamically (`SEEK_CUR`) by exact dynamic block sizing margins (`-sizeof(Student)`) to overwrite memory fields inline during updates.
 **Staging Data Removals:** Clones persistent blocks into isolated buffers (`temp.dat`) while excluding target elements, automatically handling file overwrites using file stream replacements (`remove` & `rename`).

##  File Manifest
 `Hostel_management.c` : Core application program housing structures, system menus, validation algorithms, and structural control blocks.
 `students.dat` : Binary flat-file container managed automatically by runtime processes to hold active structured relational entities securely.

## Compilation & Execution
Compile and launch the terminal binary natively utilizing standard GNU C compiler toolchains:

```bash
# Compile the C source file
gcc Hostel_management.c -o Hostel_management

# Launch the compiled binary application
./Hostel_management
