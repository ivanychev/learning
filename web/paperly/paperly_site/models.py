from __future__ import unicode_literals

from django.db import models
from django_countries.fields import CountryField
from django.contrib.auth.models import AbstractUser

# Create your models here.

class User(AbstractUser):
    first_name = models.CharField(max_length=50)
    last_name = models.CharField(max_length=50)
    interests = models.TextField()
    country = CountryField()
    avatar = models.ImageField(upload_to='avatars', blank=True, null=True)


class Review(models.Model):
    title = models.CharField(max_length=140)
    author = models.ForeignKey(User, related_name='reviews')
    body = models.TextField()
    created = models.DateTimeField(auto_now_add=True)
    # the date will be saved automatically when creating an object
    stars = models.IntegerField()

    class Meta:
        ordering = ('-created',)

class ReviewLike(models.Model):
    user = models.OneToOneField(User)
    review = models.OneToOneField(Review)

class ReviewSpoilerReport(models.Model):
    user = models.OneToOneField(User)
    review = models.OneToOneField(Review)

