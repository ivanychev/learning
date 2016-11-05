from django.db import models
from django.contrib.auth.models import AbstractUser
from django_countries.fields import CountryField

# Create your models here.

FIRST_NAME_LENGTH = 50
LAST_NAME_LENGTH = 50
TITLE_LENGTH = 140


class User(AbstractUser):
    first_name = models.CharField(max_length=FIRST_NAME_LENGTH)
    last_name = models.CharField(max_length=LAST_NAME_LENGTH)
    interests = models.TextField(blank=True, default="")
    country = CountryField(blank=True, default="")
    avatar = models.ImageField(upload_to='avatars', blank=True, null=True)
    books_status = models.ManyToManyField("book.Book", through="book.BookStatus")
    following = models.ManyToManyField("self", blank=True)

    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.first_name + " " + self.last_name
