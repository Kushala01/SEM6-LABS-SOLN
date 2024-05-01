from django.shortcuts import render,redirect
from django.http import HttpResponse
from .models import Product
from django.http import JsonResponse

# Create your views here.
def index(request):
    return render(request,'home.html')

def add_product(request):
    if request.method=='POST':
        name=request.POST.get('name')
        price=request.POST.get('price')
        Product.objects.create(name=name, price=price)
        return redirect('index')
    return render(request, 'add_product.html')

def display_product(request):
    # Filter products with price greater than 200
    products_above_200 = Product.objects.filter(price__gt=200)
    return render(request, 'display_product.html', {'products': products_above_200})

def product_detail(request, product_id):
    product=Product.objects.get(id=product_id)
    return render(request, 'product_detail.html', {'product':product})