class BaseAgent(object):
    """
    Base class for all agents.
    """

    def __init__(self, env):
        self.env = env
        self.replay_buffer = None

    def store(self, state, action, reward, next_state, done):
        """
        Store experience in replay buffer.
        """
        raise NotImplementedError

    def act(self, state):
        """
        Choose action given state.
        """
        raise NotImplementedError

    def train(self):
        """
        Train agent.
        """
        raise NotImplementedError
