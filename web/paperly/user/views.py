from django.shortcuts import render
from .models import *
from book.models import BookStatus, Book, Review, WANT_TO_READ, READ

# Create your views here.

def user_page(request, userid):
    user_now = User.objects.get(id=userid)
    return render(request, "user.html", {"user_now": user_now})

def user_books(request, userid):
    read_books = BookStatus.objects.filter(user_id=userid, status=READ)
    reading_books = BookStatus.objects.filter(user_id=userid, status=WANT_TO_READ)
    want_books = BookStatus.objects.filter(user_id=userid, status=WANT_TO_READ)
    return render(request, "read_books.html", {'read_books': read_books,
                                               'reading_books': reading_books,
                                               'want_books': want_books})
