from django.db import models

# Create your models here.
class toDoList(models.Model):
    name=models.CharField(max_length=200)
    
    def __str__(self):
        return self.name
    
class item(models.Model):
    todolist=models.ForeignKey(toDoList,on_delete=models.CASCADE)
    text=models.CharField(max_length=200)
    complete=models.BooleanField()
    
    def __str__(self):
        return self.text