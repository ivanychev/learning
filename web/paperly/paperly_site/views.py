from django.shortcuts import render
from .models import Book

# Create your views here.

def post_list(request):
    books = Book.objects.order_by('title')
    return render(request, 'list.html', {'books': books})