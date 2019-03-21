library(ggplot2)

########################################################
#               Resultats vecteurs
########################################################

vect=read.table("results_force_faible_vecteurs.txt",head=TRUE)
vect

# SOMME DE DEUX VECTEURS
thread=as.factor(vect$nb_thread)
p1<- ggplot(vect, aes(x=nb_thread, group=nb_thread, y=diff1_somme_deux_vect,fill=thread)) + 
  geom_boxplot() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Somme de deux vecteurs")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))+ 
  scale_fill_brewer(palette="Blues")

p1


# SOMME DES ELEMENTS D'UN VECTEUR
thread=as.factor(vect$nb_thread)
p2<- ggplot(vect, aes(x=nb_thread, group=nb_thread, y=diff2_somme_vect,fill=thread)) + 
  geom_boxplot() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Somme des elements d'un vecteur")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))+ 
  scale_fill_brewer(palette="Blues")

p2


# MULTIPLICATION DE DEUX VECTEURS
thread=as.factor(vect$nb_thread)
p3<- ggplot(vect, aes(x=nb_thread, group=nb_thread, y=diff3_multi_vect,fill=thread)) + 
  geom_boxplot() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Multiplication d'un vecteur par un double")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))+ 
  scale_fill_brewer(palette="Blues")

p3

########################################################
#               Resultats matrices
########################################################

mat=read.table("resultat_force_faible_10.txt",head=TRUE)
mat


# SOMME DE DEUX MATRICES
thread=as.factor(mat$nb_thread)
g1<- ggplot(mat, aes(x=nb_thread, group=nb_thread, y=diff1_somme_deux_mat,fill=thread)) + 
  geom_boxplot() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Somme de deux matrices")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))+ 
  scale_fill_brewer(palette="Blues")

g1


# SOMME DES ELEMENTS D'UNE MATRICE
thread=as.factor(mat$nb_thread)
g2<- ggplot(mat, aes(x=nb_thread, group=nb_thread, y=diff2_somme_mat,fill=thread)) + 
  geom_boxplot() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Somme des elements d'une matrice")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))+ 
  scale_fill_brewer(palette="Blues")

g2


# MULTIPLICATION DE DEUX MATRICES
thread=as.factor(mat$nb_thread)
g3<- ggplot(mat, aes(x=nb_thread, group=nb_thread, y=diff3_multi_mat,fill=thread)) + 
  geom_boxplot() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Multiplication d'une matrices par un double")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))+ 
  scale_fill_brewer(palette="Blues")

g3


########################################################
#               Resultats matrices lettre
########################################################

letter=read.table("resultats_v2_force_faible.txt",head=TRUE)
letter

dimentions=as.factor(letter$nb_rows)

l1<- ggplot(letter, aes(x=nb_thread, group=nb_thread, y=temps_comptage,fill=thread)) + 
  geom_boxplot() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Multiplication d'une matrices par un double")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))+ 
  scale_fill_brewer(palette="Blues")

l1


l2<- ggplot(letter, aes(x=nb_thread, group=nb_thread, y=temps_comptage_v2,fill=thread)) + 
  geom_boxplot() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Multiplication d'une matrices par un double")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))+ 
  scale_fill_brewer(palette="Blues")

l2

