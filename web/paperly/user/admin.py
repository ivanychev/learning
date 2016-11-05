from django.contrib import admin

# Register your models here.

from django.contrib import admin
from django.contrib.auth.admin import UserAdmin as BaseUserAdmin

from .models import *
from book.models import *



class UserAdmin(BaseUserAdmin):

    fieldsets = BaseUserAdmin.fieldsets + (
        (u'Дополнительно', {'fields': ('admin_avatar', 'avatar')}),
    )

    def admin_avatar(self, instance):
        return instance.avatar and u'<img src="{0}" width="100px" />'.format(
            instance.avatar.url
        )
    admin_avatar.allow_tags = True
    admin_avatar.short_description = u'Аватар'


MODELS = [Genre,
          Author,
          Book,
          User,
          BookStatus,
          ReviewLike,
          ReviewSpoilerReport,
          Review]

for cls in MODELS:
    admin.site.register(cls)