data=read.table("resultat_force_faible_10.txt",head=TRUE)
data

library(ggplot2)

# SOMME DE DEUX MATRICES
thread=as.factor(data$nb_thread)
g1<- ggplot(data, aes(x=nb_thread, group=nb_thread, y=diff1_somme_deux_mat,fill=thread)) + 
  geom_boxplot() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_discrete(name = "nombre de threads") +
  ggtitle("Somme de deux matrices")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))+ 
  scale_fill_brewer(palette="Blues")

g1


# SOMME DES ELEMENTS D'UNE MATRICE
thread=as.factor(data$nb_thread)
g2<- ggplot(data, aes(x=nb_thread, group=nb_thread, y=diff2_somme_mat,fill=thread)) + 
  geom_boxplot() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_discrete(name = "nombre de threads") +
  ggtitle("Somme des éléments d'une matrice")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))+ 
  scale_fill_brewer(palette="Blues")

g2


# MULTIPLICATION DE DEUX MATRICES
thread=as.factor(data$nb_thread)
g3<- ggplot(data, aes(x=nb_thread, group=nb_thread, y=diff3_multi_mat,fill=thread)) + 
  geom_boxplot() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_discrete(name = "nombre de threads") +
  ggtitle("Multiplication de deux matrices")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))+ 
  scale_fill_brewer(palette="Blues")

g3



