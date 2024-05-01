from django.contrib import admin
from django.urls import path
from . import views

urlpatterns = [
    # Uncomment the next line to enable the admin:
    path('',views.index,name='index'),
    path('add/',views.add_product, name='add_product'),
    path('display/',views.display_product,name='display_product'),
    path('product/<int:product_id>/',views.product_detail, name='product_detail'),
    path('admin/', admin.site.urls),
]