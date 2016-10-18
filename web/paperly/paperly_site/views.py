from django.shortcuts import render
from .models import *

# Create your views here.

def user_books(request, userid):
    read_books = BookStatus.objects.filter(user_id=userid, status=READ)
    reading_books = BookStatus.objects.filter(user_id=userid, status=WANT_TO_READ)
    want_books = BookStatus.objects.filter(user_id=userid, status=WANT_TO_READ)
    return render(request, "read_books.html", {'read_books': read_books,
                                               'reading_books': reading_books,
                                               'want_books': want_books})
def book(request, id):
    book = Book.objects.get(id=id)
    reviews = Review.objects.filter(book=book)
    authors = book.authors.all()
    return render(request, "book.html", {'book': book, 'reviews': reviews,
                                         'authors': authors})

def user_page(request, userid):
    user_now = User.objects.get(id=userid)
    return render(request, "user.html", {"user_now": user_now})