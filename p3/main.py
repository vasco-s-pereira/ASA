from sys import stdin
from pulp import GLPK, LpVariable, LpInteger, LpProblem, LpMaximize, lpSum, value

brinquedos_lp = {}
brinquedos = {}
prob = LpProblem("Brinquedos", LpMaximize)

(num_brinquedos, num_pacotes, max) = stdin.readline().split()
num_brinquedos = int(num_brinquedos)
num_pacotes = int(num_pacotes)
max = int(max)
lines = stdin.readlines()
for i in range(num_brinquedos):
    line = lines[i]
    (lucro, capacidade) = line.split()
    lucro = int(lucro)
    capacidade = int(capacidade)
    brinquedo = {"lucro": lucro, "capacidade": capacidade}
    brinquedos["Brinquedo" + str(i + 1)] = brinquedo
    brinquedos_lp["Brinquedo" + str(i + 1)] = \
        LpVariable("Brinquedo" + str(i + 1),
                   0, capacidade,
                   LpInteger)
pacotes = {}
pactoes_lp = {}
for i in range(num_brinquedos, num_brinquedos+num_pacotes):
    line = lines[i]
    (brinquedo1, brinquedo2, brinquedo3, lucro) = line.split()
    lucro = int(lucro)
    pacote = {"brinquedos": ["Brinquedo" + brinquedo1,
                             "Brinquedo" + brinquedo2,
                             "Brinquedo" + brinquedo3],
              "lucro": lucro}
    pacotes["Pacote" + str(i - num_brinquedos + 1)] = pacote
    up_bound = min([brinquedos[brinquedo]["capacidade"]
                    for brinquedo in pacote["brinquedos"]])
    name = "Pacote" + str(i - num_brinquedos + 1)
    pactoes_lp["Pacote" + str(i - num_brinquedos + 1)] = LpVariable(name,
                                                                    0,
                                                                    up_bound,
                                                                    LpInteger)

# Função objetivo
# Maximize lucro*quantidade
objective = lpSum([brinquedos[brinquedo]["lucro"] *
                  brinquedos_lp[brinquedo] for brinquedo in brinquedos])
objective += lpSum([pacotes[pacote]["lucro"] * pactoes_lp[pacote]
                   for pacote in pacotes])
prob += objective

for brinquedo in brinquedos:
    max_caps = []
    max_caps.append(brinquedos_lp[brinquedo])
    for pacote in pacotes:
        if brinquedo in pacotes[pacote]["brinquedos"]:
            max_caps.append(pactoes_lp[pacote])
    prob += lpSum(max_caps) <= brinquedos[brinquedo]["capacidade"]

max_caps = lpSum([3 * pactoes_lp[pacote] for pacote in pactoes_lp])
max_caps += lpSum([brinquedos_lp[brinquedo] for brinquedo in brinquedos_lp])

prob += max_caps <= max



prob.solve(GLPK(msg=False))

if prob.status == 1:
    print(value(prob.objective))
