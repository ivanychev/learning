from __future__ import unicode_literals

from django.db import models
from django_countries.fields import CountryField
from django.contrib.auth.models import AbstractUser

# Create your models here.

FIRST_NAME_LENGTH = 50
LAST_NAME_LENGTH = 50
TITLE_LENGTH = 140

# book statuses
READ = 0
NOT_READ = 1
READING = 2
WANT_TO_READ = 3

# book ratings
AWFUL = 1
BAD = 2
SOSO = 3
GOOD = 4
EXCELLENT = 5


class Genre(models.Model):
    name = models.CharField(max_length=TITLE_LENGTH)
    description = models.TextField(blank=True, default="")

    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.name


class Author(models.Model):
    first_name = models.CharField(max_length=FIRST_NAME_LENGTH)
    last_name = models.CharField(max_length=LAST_NAME_LENGTH)
    country = CountryField(blank=True, null=True)
    date_birth = models.DateField(blank=True, null=True)
    date_death = models.DateField(blank=True, null=True)
    biography = models.TextField(blank=True, default="")

    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    def __str__(self):
        return str(self.first_name) + " " + str(self.last_name)


class Book(models.Model):
    cover = models.ImageField(upload_to='covers', blank=True, null=True)
    title = models.CharField(max_length=TITLE_LENGTH, blank=False)
    description = models.TextField(blank=True, default="")
    first_published = models.DateField(blank=True, null=True)
    authors = models.ManyToManyField(Author)
    genre = models.ForeignKey(Genre)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.title


class User(AbstractUser):
    first_name = models.CharField(max_length=FIRST_NAME_LENGTH)
    last_name = models.CharField(max_length=LAST_NAME_LENGTH)
    interests = models.TextField(blank=True, default="")
    country = CountryField(blank=True, default="")
    avatar = models.ImageField(upload_to='avatars', blank=True, null=True)
    books_status = models.ManyToManyField(Book, through="BookStatus")
    following = models.ManyToManyField("self", blank=True)

    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.first_name + " " + self.last_name


class BookStatus(models.Model):
    STATUS_CHOICES = (
        (READ, 'Read'),
        (NOT_READ, 'Not read'),
        (READING, 'Reading'),
        (WANT_TO_READ, 'Want to read')
    )
    book = models.ForeignKey(Book)
    user = models.ForeignKey(User)
    status = models.IntegerField(choices=STATUS_CHOICES, default=NOT_READ)

    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.user.first_name + \
               " " + self.user.first_name + \
               " " + self.book.title + \
               " " + str(self.status)


class Review(models.Model):
    title = models.CharField(max_length=140, blank=True, default="")
    author = models.ForeignKey(User, related_name='reviews', blank=False)
    body = models.TextField(blank=True, default="")
    book = models.ForeignKey(Book, blank=False, null=False)
    # the date will be saved automatically when creating an object
    MARKS = (
        (AWFUL, "Awful"),
        (BAD, "Bad"),
        (SOSO, "So-so"),
        (GOOD, "Good"),
        (EXCELLENT, "Excellent")
    )
    stars = models.IntegerField(choices=MARKS)
    liked = models.ManyToManyField(User, through="ReviewLike",
                                        related_name="%(class)s_liked_review")
    reported = models.ManyToManyField(User, through="ReviewSpoilerReport",
                                        related_name="%(class)s_reported_review")

    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    class Meta:
        ordering = ('-created_at',)

    def __str__(self):
        return "AuthorID:" + str(self.author.id) + "|" + self.book.title


class ReviewLike(models.Model):
    user = models.OneToOneField(User)
    liked_review = models.OneToOneField(Review, related_name="%(class)s_liked")
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    def __str__(self):
        return "UserID:" + self.user.id + "|LikedReviewId:" + self.liked_review.id


class ReviewSpoilerReport(models.Model):
    user = models.OneToOneField(User)
    reported_review = models.OneToOneField(Review, related_name="%(class)s_reported")
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    def __str__(self):
        return "UserID:" + self.user.id + "|SpoiledReviewId:" + self.liked_review.id
