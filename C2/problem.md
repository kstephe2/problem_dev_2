# C2_Talk_2_ME

- Namespace: challenges
- ID: C2_Talk_2_ME
- Type: custom
- Category: Reverse Engineering
- Points: 150
- Templatable: no
- MaxUsers: 20

## Description

We captured some malware that establishes comms to a C2 server!
Sadly... it went down before we could analyze the connections.
Lucky for us a new C2 is running on port 4444. Can you figure out
how to communicate using the old sample?

Download the sample {{url_for("establish_comms", "here")}}.

## Details

`$ nc {{server}} {{port}}`

## Hints

- Patching binaries can be useful. We recommend a hex editor for this one.

- Sometimes formats swtich between ascii and bytes

## Solution Overview

This problem is solved by patching the hardcoded IP address in the binary and observing the traffic
it sends.

## Challenge Options

## Learning Objective

Expose players to basic binary patching and protocol analysis

## Attributes

- author: Kevin
