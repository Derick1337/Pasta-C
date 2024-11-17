print('cadernos =1\ncaneta_azul =2\ncaneta_vermelha =3\nBorracha =4\nLapis_macio =5')
nome=input('Qual é o seu nome?:')
caderno = 1
caneta_azul = 2
caneta_vermelha = 3
borracha = 4
lapis_macio = 5

compras = []
quantidades = [0, 0, 0, 0, 0]
itens = [caderno, caneta_azul, caneta_vermelha, borracha, lapis_macio]
precos = [10.00, 3.00, 3.00, 2.00, 1.00]

while True:
    codigo_produto = int(input('Código do produto (ou 0 para finalizar): '))

    if codigo_produto == 0:
        break

    if codigo_produto in itens:
        indice = itens.index(codigo_produto)
        quantidade = int(input('Quantidade: '))
        quantidades[indice] += quantidade
    else:
        print('Código de produto inválido.')
total = 0

for i in range(len(itens)):
    if quantidades[i] > 0:
        subtotal = quantidades[i] * precos[i]
        compras.append(f'{subtotal:.2f} {quantidades[i]} x {itens[i]}')
        total += subtotal

print('Cliente:', nome)
print('\n'.join(compras))
print('-----------')
print('{:.2f} valor total'.format(total))