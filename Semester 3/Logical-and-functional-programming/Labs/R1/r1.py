class Node:
    def __init__(self, e):
        self.elem = e
        self.next = None


class Lista:
    def __init__(self):
        self.head = None


'''
crearea unei liste din valori citite pana la 0
'''


def creareLista():
    lista = Lista()
    lista.head = creareLista_rec()
    return lista


def creareLista_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        nod = Node(x)
        nod.next = creareLista_rec()
        return nod


'''
tiparirea elementelor unei liste
'''


def tipar(lista):
    tipar_rec(lista.head)


def tipar_rec(nod):
    if nod != None:
        print(nod.elem,end=' ')
        tipar_rec(nod.next)


"""
10. a. Determine the number formed by adding all even elements and subtracting
 all odd numbers of the list.
b. Determine difference of two sets represented as lists
"""


"""
a(l1l2...ln) = {
    0, if n = 0
    a(l2...ln) + l1, l1%2 = 0
    a(l2...ln) - l1, otherwise}
"""
def a(node):  # node = lista.head
    if node is None:
        return 0
    if node.elem % 2 == 0:
        return a(node.next) + node.elem
    return a(node.next) - node.elem


def add(lista, elem):
    lista.head = addRec(lista.head, elem)
    return lista


"""
addRec(l1l2...ln,elem) = {
    (elem), if n = 0
    l1 + addRec(l2...ln,elem), otherwise}
"""
def addRec(node, elem):
    if node is None:
        return Node(elem)
    node.next = addRec(node.next, elem)
    return node


def findIn(node, elem):
    if node is None:
        return False
    if node.elem == elem:
        return True
    return findIn(node.next, elem)


"""
 difference(l1l2...ln, q1q2...qm, a1a2...ap) = {
        a1a2...an, if n = 0
        difference(l2...ln, q1q2...qm, a1a2...ap U l1), if l1 is not in q1q2...qn
        difference(l2...ln, q1q2...qm, a1a2...ap), otherwise}
"""
def difference(node1, node2, lista):
    if node1 is None:
        return lista
    if not findIn(node2, node1.elem):
        lista = add(lista, node1.elem)
    lista = difference(node1.next, node2, lista)
    return lista


def b(lista1, lista2):
    lst = Lista()
    lst = difference(lista1.head, lista2.head, lst)
    return lst


'''
program pentru test
'''


def test_a():
    list1 = Lista()  # 1 5 8 20 27
    add(list1, 1)
    add(list1, 5)
    add(list1, 8)

    assert(a(list1.head) == 2)

    add(list1, 20)
    assert(a(list1.head) == 22)

    add(list1, 27)
    assert (a(list1.head) == -5)


def test_b():
    list1 = Lista()  # 1 5 8 20
    add(list1, 1)
    add(list1, 5)
    add(list1, 8)
    add(list1, 20)

    list2 = Lista()
    add(list2, 6)
    add(list2, 8)
    add(list2, 9)
    add(list2, 18)
    add(list2, 20)

    # 1 5 8 20
    # 6 8 9 18 20
    # list3: 1 5

    lres = Lista()
    add(lres, 1)
    add(lres, 5)

    list3 = b(list1, list2)

    assert(list3.head.elem == 1)
    node = list3.head.next
    assert(node.elem == 5)


def main():
    test_a()
    test_b()

    # lista1 = creareLista()
    # tipar(lista1)
    # print("\na)")
    # print(a(lista1.head))
    # print("\nb)")
    # lista2 = creareLista()
    # bb = b(lista1, lista2)
    # tipar(bb)


main()
