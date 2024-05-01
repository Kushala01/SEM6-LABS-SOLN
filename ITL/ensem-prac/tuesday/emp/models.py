from unittest.util import _MAX_LENGTH
from django.db import models

# Create your models here.
class Product(models.Model):
    id=models.IntegerField(primary_key=True)
    name=models.CharField(max_length=200)
    price=models.IntegerField()
    
    def __str__(self):
        return self.name