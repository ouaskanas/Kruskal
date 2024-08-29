import os
import networkx as nx
import matplotlib.pyplot as plt

path = os.path.join(os.path.expanduser("~"), "Desktop\Recherche_Opérationnelle")

with open(r'path', 'r') as file:
    text1 = file.read()

with open(r'path', 'r') as file:
    text2 = file.read()

aretes = eval(text1)
aretes2 = eval(text2)

def save_graph_image(aretes, file_name, folder_path=path):
    G = nx.Graph()
    G.add_weighted_edges_from(aretes)
    pos = nx.spring_layout(G)
    labels = nx.get_edge_attributes(G, 'weight')
    nx.draw(G, pos, with_labels=True, font_weight='bold', node_size=700)
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
    file_path = os.path.join(folder_path, file_name)
    plt.savefig(file_path)
    plt.close()

save_graph_image(aretes, 'original_graph.png')

save_graph_image(aretes2, 'kruskal_mst_graph.png')
