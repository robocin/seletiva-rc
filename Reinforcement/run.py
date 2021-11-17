import argparse

import gym

from agent import DDPGAgent, DQNAgent, QLearnAgent, RandomAgent


def main(env_name, render=False):
    env = gym.make(env_name)
    # Inicialize seu agente aqui
    agent = RandomAgent(env)
    for episode_i in range(100000):
        state = env.reset()
        done = False
        while not done:
            if render and episode_i % 10 == 0:
                env.render()
            # Ação do seu agente aqui
            action = agent.act(state)
            state, reward, done, info = env.step(action)
            # Função de treino do seu agente aqui
            # Exemplo:
            # agent.store(state, action, reward, done)
            # agent.learn()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-e", "--env", required=True, help="Name of the gym environment"
    )
    parser.add_argument(
        "-r",
        "--render",
        default=False,
        action="store_true",
        help="Render every 10 episodes",
    )
    args = parser.parse_args()
    main(args.env, args.render)
