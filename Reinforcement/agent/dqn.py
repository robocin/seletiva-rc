from base_agent import BaseAgent


class DQNAgent(BaseAgent):
    def __init__(self, env):
        super(DQNAgent, self).__init__(env)

    def act(self, state):
        """
        Choose an action based on the current state
        """
        pass

    def store(self, state, action, reward, next_state, done):
        """
        Store the experience
        """
        pass

    def train(self):
        """
        Train the agent
        """
        pass
