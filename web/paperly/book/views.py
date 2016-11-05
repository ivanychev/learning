from django.shortcuts import render
from .models import *

from user.models import User
# Create your views here.

def book(request, id):
    book = Book.objects.get(id=id)
    reviews = Review.objects.filter(book=book)
    authors = book.authors.all()
    return render(request, "book.html", {'book': book, 'reviews': reviews,
                                         'authors': authors})
