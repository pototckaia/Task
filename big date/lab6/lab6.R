library("stringr")

titanic <- read.csv("titanic_train.csv")

#1. 
"Сколько мужчин / женщин находилось на борту?"
tbl <- table(titanic$Sex)
tbl
barplot(tbl)

#2. 
"Выведите распределение переменной Pclass
(социально-экономический статус) и это же
распределение, только для мужчин / женщин поотдельности. Сколько было мужчин 2-го класса?"

titanic_male <- subset(titanic, Sex == "male", names(titanic))
titanic_female <- subset(titanic, Sex == "female", names(titanic))

hist(titanic$Pclass)
hist(titanic_male$Pclass)
hist(titanic_female$Pclass)

nrow(subset(titanic, Sex == "male" & Pclass == 2))

#3. 
"Каковы медиана и стандартное отклонение платежей
(Fare)? Округлите до 2 десятичных знаков."

round(median(titanic$Fare), digits=2)
round(sd(titanic$Fare), digits=2)

#4. 
"Правда ли, что люди моложе 30 лет выживали чаще,
чем люди старше 60 лет? Каковы доли выживших в
обеих группах?"

tb30 <- subset(titanic, Age < 30, names(titanic))
tb60 <- subset(titanic, Age < 60, names(titanic))

sum(tb30$Survived) > sum(tb60$Survived)
sum(tb30$Survived) / nrow(tb30)
sum(tb60$Survived) / nrow(tb60)

#5. 
"Правда ли, что женщины выживали чаще мужчин?
Каковы доли выживших в обеих группах?"

sum(titanic_female$Survived) > sum(titanic_male$Survived)
sum(titanic_female$Survived) / nrow(titanic_female)
sum(titanic_male$Survived) / nrow(titanic_male)

#6. 
"Найдите самое популярное имя среди пассажиров
Титаника мужского пола?"

first_name = sapply(titanic_male$Name, function(x){ str_extract(str_sub(x, str_locate(x, "\\.")[1]+2), "\\w+") })
first_name = table(first_name)
first_name[which.min(first_name)]

# #7. 
"Сравните графически распределение стоимости
билетов и возраста у спасенных и у погибших.
Средний возраст погибших выше, верно?"

titanic_survived = subset(titanic, Survived == 1, names(titanic))
titanic_unsurvived = subset(titanic, Survived == 0, names(titanic))

plot(Fare ~ Age, titanic_survived, col="red")
points(Fare ~ Age, titanic_unsurvived, col="blue")
legend(60, 500, legend=c("Survived", "Unsurvived"),col=c("red", "blue"), lty=1:2)

#8. 
"Как отличается средний возраст мужчин / женщин в
зависимости от класса обслуживания?"

# aggregate(titanic_male, list(titanic_male$Pclass), mean)


sub_titanic <- subset(titanic, select=c('Age', 'Pclass', 'Sex'))
sub_titanic <- na.omit(sub_titanic)
agg <- aggregate(
	sub_titanic, 
	by=list(sub_titanic$Sex, sub_titanic$Pclass), FUN=mean)


agg_male = subset(agg, Group.1 == 'male', select=c('Age', 'Pclass'))
agg_male
agg_female = subset(agg, Group.1 == 'female', select=c('Age', 'Pclass'))
agg_female

plot(Age ~ Pclass, agg_female, col="blue",  ylim=c(15,45))
points(Age ~ Pclass, agg_male, col="red")
legend(2, 40, legend=c("Male", "Female"),col=c("red", "blue"), lty=c(1,1))
