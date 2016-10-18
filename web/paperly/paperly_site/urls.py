from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^user/(?P<userid>\w{1,50}$)', views.user_page),
    # url(r'^author/(?P<id>[0-9]+)', views.author),
    url(r'^book/(?P<id>[0-9]+)', views.book),
    # url(r'^book/create', views.create_book),
    # url(r'^user/reviews', views.user_reviews),
    url(r'^user/(?P<userid>\w{1,50})/books', views.user_books),
    # url(r'^updates', views.updates),
    # url(r'^explore', views.explore),
]