# C Facts
I dont want to create a new example file for every new thing i discover about C so I'll add the smaller things I find out here.

## file descriptors
New File descriptors are assigned in the following way:
1, 2, 3 are preassigned; then when new ones are created, the lowest-numbered unused descriptor is used
Ref: `man dup`
