from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^user/(?P<userid>\w{1,50}$)', views.user_page),
    url(r'^user/(?P<userid>\w{1,50})/books', views.user_books)
]