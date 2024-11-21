# Análise dos Gráficos de Esforço Computacional para Operações de Adição e Remoção

Este projeto analisa o esforço computacional necessário para realizar operações de **adição** e **remoção** em diferentes tipos de árvores balanceadas: **Árvore Rubro-Negra (RN)**, **Árvore AVL**, e **B-árvores** com diferentes ordens (**B-1**, **B-5**, **B-10**), para diferentes tamanhos de conjuntos de dados.

## 1. Análise do Esforço Computacional na Operação de Adição

### Resultados da Operação de Adição:
Ao analisar os dados de adição, podemos observar que o **esforço computacional** (indicando o número de operações ou tempo gasto) aumenta com o crescimento do conjunto de dados (representado pela variável `n`). O comportamento de cada estrutura de árvore segue uma tendência semelhante de aumento do esforço com o aumento de `n`, mas com algumas diferenças notáveis entre os tipos de árvore.

#### Observações:
1. **Árvore Rubro-Negra (RN)**:
   - A Rubro-Negra apresenta o **menor esforço computacional** entre todas as árvores, tanto em termos de número de operações quanto de tempo. Isso se deve à sua estrutura de balanceamento eficiente, que permite operações de inserção (adição) mais rápidas, especialmente para conjuntos de dados menores.
   - A curva de esforço cresce de forma **suave**, refletindo uma inserção eficiente mesmo à medida que o conjunto de dados aumenta.

2. **Árvore AVL**:
   - A árvore AVL exige **um pouco mais de esforço** do que a Rubro-Negra, especialmente à medida que o tamanho do conjunto de dados aumenta. Isso pode ser atribuído ao seu método de balanceamento, que exige verificações e rotações adicionais em cada operação de inserção.
   - A curva de esforço cresce de forma **mais acentuada** em comparação à Rubro-Negra, indicando uma maior complexidade à medida que `n` aumenta.

3. **B-Árvores (B-1, B-5, B-10)**:
   - As B-árvores, especialmente as de ordem maior (B-5 e B-10), exigem um esforço significativamente maior em relação à Rubro-Negra e AVL. O aumento do número de elementos em uma B-árvore envolve a manutenção do balanceamento de uma estrutura com múltiplos filhos por nó, o que torna a operação mais custosa.
   - A curva de esforço dessas árvores segue uma **tendência mais acentuada** à medida que o tamanho do conjunto de dados aumenta. Isso se deve à necessidade de reorganizar mais dados para manter as propriedades de balanceamento das B-árvores, especialmente em ordens mais altas.

#### Resumo:
- **Rubro-Negra**: Menor esforço computacional e crescimento suave da curva.
- **AVL**: Maior esforço em relação à Rubro-Negra, especialmente com grandes conjuntos de dados.
- **B-árvores**: Maior esforço computacional, com um crescimento de curva mais acentuado, especialmente para ordens mais altas.

## 2. Análise do Esforço Computacional na Operação de Remoção

### Resultados da Operação de Remoção:
Os resultados da remoção indicam o esforço necessário para remover elementos das diferentes árvores. Semelhante à operação de adição, o esforço computacional aumenta com o aumento do tamanho do conjunto de dados, mas com diferenças específicas dependendo da estrutura da árvore.

#### Observações:
1. **Árvore Rubro-Negra (RN)**:
   - A Rubro-Negra continua a demonstrar **o menor esforço computacional** nas operações de remoção. Isso é consistente com os resultados da adição, já que a árvore Rubro-Negra é bem equilibrada e suas operações de remoção não são tão custosas em termos de reestruturação da árvore.
   - A curva de remoção também apresenta um crescimento **suave**, refletindo a eficiência da árvore Rubro-Negra.

2. **Árvore AVL**:
   - A AVL, mais uma vez, apresenta um **maior esforço** do que a Rubro-Negra, especialmente para grandes conjuntos de dados. Como a operação de remoção envolve a reorganização dos nós e verificações de balanceamento, o esforço aumenta significativamente.
   - A curva de remoção da AVL é **mais íngreme** do que a da Rubro-Negra, refletindo a maior complexidade de balanceamento envolvida na remoção de elementos.

3. **B-Árvores (B-1, B-5, B-10)**:
   - As B-árvores continuam a exigir o **maior esforço computacional** para a remoção, especialmente à medida que o tamanho do conjunto de dados cresce. A remoção de elementos em uma B-árvore implica na reorganização de múltiplos nós e na manutenção do balanceamento da estrutura, o que é um processo mais complexo.
   - A curva de esforço para as B-árvores segue um crescimento **mais acentuado**, especialmente para ordens maiores. Isso se deve ao fato de que a estrutura de uma B-árvore, com vários filhos por nó, requer mais operações para manter a ordem e balanceamento da árvore durante a remoção.

#### Resumo:
- **Rubro-Negra**: Menor esforço computacional nas remoções, com crescimento suave da curva.
- **AVL**: Maior esforço do que a Rubro-Negra, especialmente para grandes conjuntos de dados, devido ao balanceamento.
- **B-árvores**: Maior esforço computacional, com curvas de crescimento mais acentuadas devido à complexidade do balanceamento.

## Conclusões Gerais:
- **Rubro-Negra** é a estrutura mais eficiente em termos de esforço computacional tanto para adição quanto para remoção, com um crescimento suave à medida que o tamanho do conjunto de dados aumenta.
- **AVL** apresenta maior complexidade, mas ainda é eficiente, embora o esforço aumente de forma mais acentuada à medida que `n` cresce.
- **B-árvores**, especialmente as de ordem maior, exigem o maior esforço computacional para as operações de adição e remoção, com curvas de crescimento mais íngremes. Isso é esperado, dado que o balanceamento e a reorganização de múltiplos filhos por nó em cada operação tornam a estrutura mais custosa.

Essas análises fornecem insights sobre qual árvore balanceada escolher, dependendo do tipo de operação e do tamanho dos dados que se espera manipular. Para operações que envolvem conjuntos de dados maiores e exigem maior eficiência, a **Rubro-Negra** pode ser a escolha mais adequada, enquanto para cenários que envolvem grandes quantidades de dados com múltiplos filhos por nó, as **B-árvores** podem ser mais vantajosas, apesar do maior custo computacional.