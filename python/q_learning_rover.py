"""
Smart Mars Rover AI - Q-Learning Core
--------------------------------------
A minimal tabular Q-learning setup for the rover's decision-making.

State:  tuple of sensor readings (currently a placeholder - see get_state)
Action: one of ['forward', 'left', 'right', 'stop']
Reward: +10 for a safe move (placeholder - wire this to real collision logic
        later), used to update the Q-table via the standard Q-learning
        update rule.

This is the SIMULATION side of the project. The Arduino sketch
(arduino/rover_obstacle_avoidance.ino) currently runs its own simple
reflex logic independently. A future step is to connect this Q-table
to the real rover over serial (see pyserial) so the learned policy -
not just the reflex rule - controls the hardware.
"""

import random

# ---- Actions available to the rover ----
actions = ['forward', 'left', 'right', 'stop']

# ---- Q-table: maps state -> {action: value} ----
q_table = {}


def get_state(sensor_data):
    """
    Convert raw sensor input into a hashable state.
    Currently just wraps the sensor list into a tuple so it can be
    used as a dictionary key. Replace with real discretized sensor
    readings (e.g. distance buckets) as the project matures.
    """
    return tuple(sensor_data)


def choose_action(state, epsilon=0.2):
    """
    Epsilon-greedy action selection.
    - With probability `epsilon`, explore (pick a random action).
    - Otherwise, exploit (pick the best known action for this state).
    """
    if random.uniform(0, 1) < epsilon:
        return random.choice(actions)  # Explore
    else:
        return max(
            q_table.get(state, {}),
            key=q_table.get(state, {}).get,
            default=random.choice(actions)
        )  # Exploit


def update_q_table(state, action, reward, next_state, alpha=0.1, gamma=0.9):
    """
    Standard Q-learning update:
        Q(s,a) <- Q(s,a) + alpha * (reward + gamma * max(Q(s')) - Q(s,a))
    """
    old_value = q_table.get(state, {}).get(action, 0)
    next_max = max(q_table.get(next_state, {}).values(), default=0)
    new_value = old_value + alpha * (reward + gamma * next_max - old_value)

    if state not in q_table:
        q_table[state] = {}
    q_table[state][action] = new_value


if __name__ == "__main__":
    # Example training loop (placeholder environment).
    # Replace the fixed sensor inputs and reward with a real simulated
    # or hardware-fed environment as the project progresses.
    for episode in range(1000):
        state = get_state([0, 1])       # Example sensor input
        action = choose_action(state)
        reward = 10                      # Placeholder: assume success
        next_state = get_state([1, 0])   # Example next-state input
        update_q_table(state, action, reward, next_state)

    print(f"Training complete. Q-table has {len(q_table)} states.")