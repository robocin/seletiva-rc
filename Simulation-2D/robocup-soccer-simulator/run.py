#!/usr/bin/env python
# encoding: utf-8
import os
import subprocess
import time
import sys

SERVER_BIN = 'rcssserver'
MONITOR_BIN = 'rcssmonitor'
TEAM1_BIN = 'python2 ~/simulation-2d-agent/src/agent.py LOLO 11'
TEAM2_BIN = 'python2 ~/simulation-2d-agent/src/agent.py PANDA 11'

processes, necProcesses = [], []


def launch(cmd, name = 'Unknown', necessary = True, suppressOutput = True):
    """Launch a process.
    Appends to list of processes and (optionally) necProcesses if
    necessary flag is True.
    Returns: The launched process.
    """
    kwargs = {}
    if suppressOutput:
        kwargs = {'stdout': open(os.devnull, 'w'),
                'stderr': open(os.devnull, 'w')}
    try:
        print(cmd)
        p = subprocess.Popen(cmd.split(' '), shell = False, **kwargs)
    except (IOError, OSError):
        print("ERROR: Unsuccessful launch of process {!r}".format(cmd))
        raise
    processes.append(p)
    if necessary:
        necProcesses.append([p,name])
    return p

def main():
    num_agents   = 11
    binary_dir   = os.path.dirname(os.path.realpath(__file__))
    serverCommand = SERVER_BIN

    try:
    # Launch the Server
        server = launch(serverCommand, name='server', suppressOutput=None)
        time.sleep(0.2)
        assert server.poll() is None,\
            '[run.py] Failed to launch Server with command: \"%s\"' \
            '\n\nAnother rcssserver may be running on the same port?' \
            '\nTry: \"killall -9 rcssserver\"' \
            %(serverCommand)
    #Launch the monitor        
        monitorCommand = MONITOR_BIN
        launch(monitorCommand, name='monitor').wait()
        time.sleep(5)
    except KeyboardInterrupt:
        print('[run.py] Exiting for CTRL-C')
    finally:
        print('[run.py] Cleaning up server and other processes')
        for p in reversed(processes):
            try:
                p.terminate()
                time.sleep(0.1)
                p.kill()
            except:
                pass

if __name__ == '__main__':
    main()
