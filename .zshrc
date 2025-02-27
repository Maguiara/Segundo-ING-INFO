# If you come from bash you might have to change your $PATH.
# export PATH=$HOME/bin:/usr/local/bin:$PATH

# Path to your oh-my-zsh installation.
  export ZSH=~/.oh-my-zsh

# Set name of the theme to load. Optionally, if you set this to "random"
# it'll load a random theme each time that oh-my-zsh is loaded.
# See https://github.com/robbyrussell/oh-my-zsh/wiki/Themes
ZSH_THEME="pixegami-agnoster"

# Set list of themes to load
# Setting this variable when ZSH_THEME=random
# cause zsh load theme from this variable instead of
# looking in ~/.oh-my-zsh/themes/
# An empty array have no effect
# ZSH_THEME_RANDOM_CANDIDATES=( "robbyrussell" "agnoster" )

# Uncomment the following line to use case-sensitive completion.
# CASE_SENSITIVE="true"

# Uncomment the following line to use hyphen-insensitive completion. Case
# sensitive completion must be off. _ and - will be interchangeable.
# HYPHEN_INSENSITIVE="true"

# Uncomment the following line to disable bi-weekly auto-update checks.
# DISABLE_AUTO_UPDATE="true"

# Uncomment the following line to change how often to auto-update (in days).
# export UPDATE_ZSH_DAYS=13

# Uncomment the following line to disable colors in ls.
# DISABLE_LS_COLORS="true"

# Uncomment the following line to disable auto-setting terminal title.
# DISABLE_AUTO_TITLE="true"

# Uncomment the following line to enable command auto-correction.
# ENABLE_CORRECTION="true"

# Uncomment the following line to display red dots whilst waiting for completion.
# COMPLETION_WAITING_DOTS="true"

# Uncomment the following line if you want to disable marking untracked files
# under VCS as dirty. This makes repository status check for large repositories
# much, much faster.
# DISABLE_UNTRACKED_FILES_DIRTY="true"

# Uncomment the following line if you want to change the command execution time
# stamp shown in the history command output.
# The optional three formats: "mm/dd/yyyy"|"dd.mm.yyyy"|"yyyy-mm-dd"
# HIST_STAMPS="mm/dd/yyyy"

# Would you like to use another custom folder than $ZSH/custom?
# ZSH_CUSTOM=/path/to/new-custom-folder

# Which plugins would you like to load? (plugins can be found in ~/.oh-my-zsh/plugins/*)
# Custom plugins may be added to ~/.oh-my-zsh/custom/plugins/
# Example format: plugins=(rails git textmate ruby lighthouse)
# Add wisely, as too many plugins slow down shell startup.
plugins=(
  git
  zsh-syntax-highlighting
  zsh-autosuggestions
  sudo
)

source $ZSH/oh-my-zsh.sh

# User configuration

# export MANPATH="/usr/local/man:$MANPATH"

# You may need to manually set your language environment
# export LANG=en_US.UTF-8

# Preferred editor for local and remote sessions
# if [[ -n $SSH_CONNECTION ]]; then
#   export EDITOR='vim'
# else
#   export EDITOR='mvim'
# fi

# Compilation flags
# export ARCHFLAGS="-arch x86_64"

# ssh
# export SSH_KEY_PATH="~/.ssh/rsa_id"

# Set personal aliases, overriding those provided by oh-my-zsh libs,
# plugins, and themes. Aliases can be placed here, though oh-my-zsh
# users are encouraged to define aliases within the ZSH_CUSTOM folder.
# For a full list of active aliases, run `alias`.
#
# Example aliases
# alias zshconfig="mate ~/.zshrc"
# alias ohmyzsh="mate ~/.oh-my-zsh"
#
######################################
# CONFIGURACIón PERSONAL @acoidan
#####################################
function cya() {
  clear
  ssh cya
}

function ggit() {
    # Verificar si se proporcionó un mensaje de commit
    if [[ -z "${1}" ]]; then
        echo -e "\n[ERROR] Debes proporcionar un mensaje para el commit"
        echo -e "Uso: ggit \"mensaje del commit\"\n"
        return 1
    fi

    # Verificar si estamos en un repositorio git
    if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
        echo -e "\n[ERROR] No estás en un repositorio git\n"
        return 1
    fi

    # Verificar si hay cambios para commitear
    if [[ -z "$(git status --porcelain)" ]]; then
        echo -e "\n[INFO] No hay cambios para commitear\n"
        return 0
    fi

    # Git add
    echo -e "\n[INFO] Ejecutando git add ."
    if ! git add .; then
        echo -e "\n[ERROR] Error al ejecutar git add\n"
        return 1
    fi
    echo -e "[✓] Git add completado con éxito\n"

    # Git commit
    echo -e "[INFO] Ejecutando git commit con mensaje: ${1}"
    if ! git commit -m "${1}"; then
        echo -e "\n[ERROR] Error al ejecutar git commit\n"
        return 1
    fi
    echo -e "[✓] Git commit completado con éxito\n"

    # Verificar si hay una rama remota configurada
    if ! git remote get-url origin >/dev/null 2>&1; then
        echo -e "[ERROR] No hay un repositorio remoto configurado\n"
        return 1
    fi

    # Git push
    echo -e "[INFO] Ejecutando git push"
    if ! git push; then
        echo -e "\n[ERROR] Error al ejecutar git push\n"
        return 1
    fi
    echo -e "[✓] Git push completado con éxito\n"

    # Mostrar estado final
    echo -e "\n[✓] Proceso completado exitosamente"
    echo -e "- Rama actual: $(git branch --show-current)"
    echo -e "- Último commit: $(git log -1 --pretty=format:'%h - %s')\n"
}




alias qtsp="LANG=C qtspim"

export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion

alias cat='bat'
alias catn='bat --style-plain'
alias catnp='bat --style-plain --paging=never'

alias ll='lsd -lh -group-dirs=first'
alias la='lsd -a -group-dirs=first'
alias l='lsd --group-dirs=first'
alias lla='lsd -lha --group-dirs=first'
alias ls='lsd --group-dirs=first'

alias vim='nvim'
