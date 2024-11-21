# Carregar as bibliotecas necessárias
library(ggplot2)
library(tidyr)
library(scales)  # Para formatar os rótulos dos eixos

# Defina o caminho completo para os arquivos CSV
diretorio <- "C:/projects/c-projects/ArvoresBalanceadas-Complexidade/csv/"

# Ler os dados de adição e remoção a partir do diretório especificado
adicao <- read.csv(paste0(diretorio, "resultadoAdicao.csv"), sep=";")
remocao <- read.csv(paste0(diretorio, "resultadoRemocao.csv"), sep=";")

# Converter os dados em formato longo usando 'gather()' do pacote tidyr
adicao_long <- adicao %>%
  gather(key = "Arvore", value = "Operacao", -n)  # Mantendo 'n' e transformando as outras colunas
remocao_long <- remocao %>%
  gather(key = "Arvore", value = "Operacao", -n)  # Mantendo 'n' e transformando as outras colunas

# Gráfico de adição sem notação científica no eixo Y
p_adicao <- ggplot(adicao_long, aes(x = n, y = Operacao, color = Arvore)) +
  geom_line() +
  theme_minimal() +
  labs(title = "Esforço Computacional na Operação de Adição",
       x = "Tamanho do Conjunto de Dados",
       y = "Esforço Computacional") +
  scale_color_manual(values = c("red", "blue", "green", "purple", "orange")) +
  scale_y_continuous(labels = scales::comma_format()) +  # Evitar notação científica no eixo Y e usar vírgulas
  theme(legend.title = element_blank())

# Gráfico de remoção sem notação científica no eixo Y
p_remocao <- ggplot(remocao_long, aes(x = n, y = Operacao, color = Arvore)) +
  geom_line() +
  theme_minimal() +
  labs(title = "Esforço Computacional na Operação de Remoção",
       x = "Tamanho do Conjunto de Dados",
       y = "Esforço Computacional") +
  scale_color_manual(values = c("red", "blue", "green", "purple", "orange")) +
  scale_y_continuous(labels = scales::comma_format()) +  # Evitar notação científica no eixo Y e usar vírgulas
  theme(legend.title = element_blank())

# Exibir os gráficos
print(p_adicao)
print(p_remocao)

# Salvar os gráficos em arquivos PNG no diretório especificado
ggsave(paste0(diretorio, "grafico_adicao.png"), p_adicao)
ggsave(paste0(diretorio, "grafico_remocao.png"), p_remocao)

# Mensagem final para confirmar a execução
cat("Os gráficos foram gerados e salvos como 'grafico_adicao.png' e 'grafico_remocao.png'.")
