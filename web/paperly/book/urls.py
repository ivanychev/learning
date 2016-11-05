
from django.conf.urls import include, url
from django.contrib import admin
from . import views

urlpatterns = [# url(r'^author/(?P<id>[0-9]+)', views.author),
    url(r'^book/(?P<id>[0-9]+)', views.book),
    # url(r'^book/create', views.create_book),
    # url(r'^user/reviews', views.user_reviews),
    # url(r'^updates', views.updates),
    # url(r'^explore', views.explore),
]