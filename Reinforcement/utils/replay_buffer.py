class ReplayBuffer:
    def __init__(self, buffer_size):
        self.buffer_size = buffer_size
        self.count = 0
        # Modifique o self.buffer para o que voce quiser
        self.buffer = None
    
    def add(self, experience):
        pass
    
    def sample(self, batch_size):
        pass