@echo off
setlocal enabledelayedexpansion

set problems=bur26a chr12a chr22a els19 esc32e had16 lipa20a lipa40a lipa90a nug16a nug28 rou12 scr12 sko100a tai15a

for %%p in (%problems%) do (
    echo Running a.exe with argument: %%p "VanillaTabuSearchSolver" 
    a.exe %%p "VanillaTabuSearchSolver" 
)
