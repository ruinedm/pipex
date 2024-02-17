#!/bin/bash

# Set the PID of the process you want to monitor
PID="30056"

echo "INITIAL COUNT $PID: $initial_count"
# Monitor for new file descriptors associated with the process
while true; do
    # Count current file descriptors associated with the process
    current_count=$(lsof -p "$PID" | wc -l)

    # Check if there are new file descriptors
    if [ "$current_count" -gt "$initial_count" ]; then
        echo "New file descriptor(s) created for process $PID:"
        lsof -p "$PID" | tail -n 1
    fi

    # Update the initial count
    initial_count="$current_count"

    # Sleep for some time before checking again
    sleep 1
done
