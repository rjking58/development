

some notes are in order here..

The original VC 6 projects did NOT cleanly come into VC12..

1) the projects auto-magically embed the manifests.. which hides things.. that is first thing to change to make it easier to debug...
2) the sxstrace utility was required to determine where there were issues with side by side loading (must be differences in the loader between Win XP and now)
3) this name was placed in the manifest tool config pages:  Manifest Tool -> Input/Output -> Output Manifest File -> $(OutDir)SideBySide.X.manifest  
   the actual name used is important, because the sxs system determines that from the class name (use of the sxstrace file highlighted this)
4) the UAC enablement for the manifest must be OFF for this to work (since it interferes with parsing by the sxs subsystem):  set this field as shown:
    Linker -> Manifest File -> Enable User Account Control (UAC) -> No (/MANIFESTUAC:NO)