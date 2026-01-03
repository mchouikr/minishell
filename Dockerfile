FROM debian:bookworm-slim

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        clang \
        make \
        libreadline-dev \
        valgrind \
    && rm -rf /var/lib/apt/lists/*

COPY docker/entrypoint.sh /usr/local/bin/minishell-entrypoint.sh
RUN chmod +x /usr/local/bin/minishell-entrypoint.sh

WORKDIR /workspace

ENV VALGRIND_FLAGS="--leak-check=full --show-leak-kinds=all --track-origins=yes"

ENTRYPOINT ["/usr/local/bin/minishell-entrypoint.sh"]
CMD ["bash"]
