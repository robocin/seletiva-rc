from base_agent import BaseAgent


class RandomAgent(BaseAgent):
    def __init__(self, env):
        super(RandomAgent, self).__init__(env)

    def act(self, state):
        """
        Choose an action based on the current state
        """
        pass
